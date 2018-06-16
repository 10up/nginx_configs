location ~* xmlrpc.php$ {

	# Identify Jetpack by user agent. A more secure way is by IP address.
	# See below to understand why this is the preferred method.
	set $is_jetpack_ua 0;
	if ($http_user_agent = "Jetpack by WordPress.com" ) {
			set $is_jetpack_ua 1;
	}

	set $do_block_xmlrpc "${allow_jetpack}${is_xmlrpc_whitelist_ip}${is_jetpack_ua}${is_automattic_ip}";


	# Don't allow Jetpack, not a whitelisted IP = redirect to homepage
	if ($do_block_xmlrpc ~* "^00.*") { return 403; }

	# Allow Jetpack by UA, not a whitelisted IP, not the Jetpack UA = block
	if ($do_block_xmlrpc ~* "ua00\d") { return 403; }

	# Allow Jetpack by UA and IP, not a whitelisted IP, is the Jetpack UA, but not the Jetpack IP = block
	if ($do_block_xmlrpc ~* "ip010") { return 403; }

	## All other connections are allowed ##

	# Parse the PHP - this cannot be included in an if block
	include nginx_configs/includes/php.inc;

}
