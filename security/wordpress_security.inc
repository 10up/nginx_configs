# Instead of blocking requests with a 403 Denied status, use a redirect to the homepage instead.
# The reasoning behind this is that by returning a 403, we broadcast what is a sensitive file
# which could be used by bad guys to draw conclusions about what kind of CMS or technology we
# are using on this server.  A redirect give a less clear message and keeps our technology more
# obfuscated.  Here we set the 
set $redirect_to $scheme://$host;

# Deny all attempts to access hidden files such as .htaccess, .htpasswd, .DS_Store (Mac).
# uses regex negative lookahead to allow use of letsencrypt webroot authentication
# in the .wellknown directory
location ~ /\.(?!well\-known) { deny  all; auth_basic off;}

# Prevent access to any files starting with a $ (usually temp files)
location ~ ~$ { deny all; }

# Common deny or internal locations, to help prevent access to areas of
# the site that should not be public
location ~* wp-admin/includes { deny all; }
location ~* wp-includes/theme-compat/ { deny all; }
location ~* wp-includes/js/tinymce/langs/.*\.php { deny all; }
location ~* wp-includes/js/swfupload/swfupload.swf { deny all; }
location ~* ^/wp-includes/js/mediaelement/.*.swf$ { deny all; }

# Deny access to .php files in the /wp-content/ directory (including sub-folders)
location ~* ^/wp-content/.*.(php|phps)$ { return 301 $redirect_to; }

# Deny access to any files with a .php extension in the uploads directory (redundant with previous rule)
location ~* ^/wp-content/uploads/.*.php$ { return 301 $redirect_to; }

# Block common exploit requests
location ~* (/license.txt|/phpmyadmin|/ckeditor|/hp/|/cfdocs/|/cfappman/|/SiteServer/|/webmail/|/nsn/|/servlet|/etc/passwd|/phpbb|/horde/|/administrator/|phpinfo|info.php/|/cbms/|/readme.html) {
	return 301 $redirect_to;
}


# Block by file type
location ~* \.(sql|sql\.gz|sql\.zip|tar|tar\.gz|lzma|pem|cer|crt|key|jks|asp|aspx|cgi|pwd|nsf|exe|sh|csh|pl|tmp|swp)$ {
	return 301 $redirect_to;
}

# Block access to wp-config.php and any files similarly named
location ~* /wp-config {
    return 301 $redirect_to;
}

# Prevent Nginx from announcing which version is running to the client.
# Danger is minor from leaving this on, but reducing the amount of
# invormation about the server environment is always good.
server_tokens off;
