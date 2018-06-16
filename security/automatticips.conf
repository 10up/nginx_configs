
# Note that using the Automattic IP to match can be dangerous. This is the most secure method,
# but must be frequently updated with new IP addresses (see 'scripts/update-automattic-ips.py').
# The ticket https://github.com/Automattic/jetpack/issues/1719 contains a discussion of why
# this is dangerous.

# Automattic's netblocks
geo $is_automattic_ip {
	default 0; # Block everything not in the ranges below
	64.34.206.0/24 1;
	66.155.105.128/26 1;
	69.90.253.0/24 1;
	76.74.248.128/25 1;
	76.74.255.0/25 1;
	192.0.64.0/18 1;
	198.181.116.0/22 1;
	2001:1978:1e00:3::/64 1;
	2620:115:c000::/40 1;

}
