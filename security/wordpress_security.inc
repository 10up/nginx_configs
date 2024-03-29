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
location ~* wp-includes/js/swfupload/swfupload\.swf { deny all; }
location ~* ^/wp-includes/js/mediaelement/.*\.swf$ { deny all; }

# Since wp-admin pages are not cached, block WordPress installation pages to 
# avoid brute force attacks and for obscurity.
# This will block the "5 minute" web-based install process and require WP-CLI or 
# manual wp-config.php set-up for new installations.
location ~* wp-admin/(install|setup-config)\.php$ { return 301 $redirect_to; }

# Deny access to .php files in the /wp-content/ directory (including sub-folders)
location ~* ^/wp-content/.*\.(php|phps)$ { return 301 $redirect_to; }

# Deny access to any files with a .php extension in the uploads directory (redundant with previous rule)
location ~* ^/wp-content/uploads/.*\.php$ { return 301 $redirect_to; }

# Block common exploit requests
location ~* (/license\.txt|/phpmyadmin|/ckeditor|/hp/|/cfdocs/|/cfappman/|/SiteServer/|/webmail/|/nsn/|/servlet|/etc/passwd|/phpbb|/horde/|/administrator/|phpinfo|info\.php/|/cbms/|/readme\.html|readme\.md|readme\.txt|readme|composer\.json|composer\.lock|package\.json|package\.lock) {
	return 301 $redirect_to;
}

# Block by file type
location ~* \.(sql|sql\.gz|sql\.zip|tar|tar\.gz|lzma|pem|cer|crt|key|jks|asp|aspx|cgi|pwd|nsf|exe|sh|csh|pl|tmp|swp|bak|bak2)$ {
	return 301 $redirect_to;
}

# Block access to wp-config.php and any files similarly named
location ~* /wp-config {
    return 301 $redirect_to;
}

# Block user enumeration to protect user names
# By default, WordPress redirects example.com/?author=1 to example.com/author/username

# we will always redirect...
set $force_author_redirect 1;

# unless there is no author param in the query params
if ($args !~* author=[0-9]) {
  set $force_author_redirect 0;
}

# or we are in the admin
if ($uri ~* wp-admin) {
  set $force_author_redirect 0;
}

# if both author is in the URL/query param then we are not in wp-admin redirect
if ($force_author_redirect) {
  return 301 $redirect_to;
}

# Prevent Nginx from announcing which version is running to the client.
# Danger is minor from leaving this on, but reducing the amount of
# invormation about the server environment is always good.
server_tokens off;
