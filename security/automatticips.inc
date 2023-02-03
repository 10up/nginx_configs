
# Note that using the Automattic IP to match can be dangerous. This is the most secure method,
# but must be frequently updated with new IP addresses (see 'scripts/update-automattic-ips.py').
# The ticket https://github.com/Automattic/jetpack/issues/1719 contains a discussion of why
# this is dangerous.

# Automattic's netblocks
geo $is_automattic_ip {
	default 0; # Block everything not in the ranges below
	45.121.180.0/22 1;
	64.34.206.0/24 1;
	66.155.105.128/26 1;
	69.90.253.0/24 1;
	74.114.152.0/22 1;
	76.74.248.128/25 1;
	76.74.255.0/25 1;
	103.62.32.0/22 1;
	103.115.8.0/22 1;
	185.64.140.0/22 1;
	185.138.28.0/22 1;
	192.0.64.0/18 1;
	195.234.108.0/22 1;
	196.41.85.0/24 1;
	198.181.116.0/22 1;
	200.9.112.0/23 1;
	2001:1978:1e00:3::/64 1;
	2001:43f8:bf0::/48 1;
	2402:dac0::/32 1;
	2403:6b80::/32 1;
	2620:115:c000::/40 1;
	2801:80:1610::/48 1;
	2a04:fa80::/29 1;

}
