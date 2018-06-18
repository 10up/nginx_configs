#!/usr/bin/env python

# Update list of Automattic's IP addresses to lock-down Nginx
# Run: python -uB scripts/update-automattic-ips.py | tee security/automatticips.inc
# Complains: isaac.uribe@10up.com

import netaddr
import urllib2
import xmltodict
from jinja2 import Template
import socket
import re

def whois_query(whoisServer, query):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((whoisServer, 43))
    s.send("%s\r\n" % query)
    result = ""
    while True:
        buffer = s.recv(512)
        if not buffer:
            break
        result += buffer.replace("\r\n", "\n")
    return result

# Pulling from RADB's Whois
cidrs = re.findall(r'[a-f0-9\.:\[\]]+/[0-9]+', whois_query('whois.radb.net', '-i origin AS2635'), re.IGNORECASE)

# Pulling from ARIN and cycling through their own definition of networks
org_data = xmltodict.parse(urllib2.urlopen('http://whois.arin.net/rest/org/AUTOM-93/nets').read())
for net in org_data['nets']['netRef']:
    net_data = xmltodict.parse(urllib2.urlopen(net['#text']).read())
    cidrs.append('%s/%s' % (net_data['net']['startAddress'], net_data['net']['netBlocks']['netBlock']['cidrLength']))

# Generate Nginx include file, compressing networks in case there are overlapping networks.
print Template("""
# Note that using the Automattic IP to match can be dangerous. This is the most secure method,
# but must be frequently updated with new IP addresses (see 'scripts/update-automattic-ips.py').
# The ticket https://github.com/Automattic/jetpack/issues/1719 contains a discussion of why
# this is dangerous.

# Automattic's netblocks
geo $is_automattic_ip {{ '{' }}
\tdefault 0; # Block everything not in the ranges below
{% for cidr in cidrs %}\t{{cidr}} 1;\n{% endfor %}
{{ '}' }}""").render(cidrs=netaddr.cidr_merge(cidrs))
