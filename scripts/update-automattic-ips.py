#!/usr/bin/env python

# Update list of Automattic's IP(v4) addresses for Nginx filtering
# Run: python -uB scripts/update-automattic-ips.py | tee security/automatticips.conf
# Complains: isaac.uribe@10up.com

import netaddr
import urllib2
import xmltodict
from jinja2 import Template

cidrs = []
org_data = xmltodict.parse(urllib2.urlopen('http://whois.arin.net/rest/org/AUTOM-93/nets').read())
for thing in org_data['nets']['netRef']:
    net_data = xmltodict.parse(urllib2.urlopen(thing['#text']).read())
    cidrs.append('%s/%s' % (net_data['net']['startAddress'], net_data['net']['netBlocks']['netBlock']['cidrLength']))

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
