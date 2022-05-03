	# prevent PHP path-walking exploit, remove if PHP files are on remote servers
	try_files $uri =404;
	
	# enable and secure PATH_INFO variable
	# activate PATH_INFO in php.ini with `cgi.fix_pathinfo = 1;`
	fastcgi_split_path_info ^(.+\.php)(/.+)$;
	fastcgi_param PATH_INFO $fastcgi_path_info;

	include /etc/nginx/fastcgi_params;
	
	# "php" is defined as an upstream server in nginx.conf 
	fastcgi_pass php;

	fastcgi_index index.php;
	fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;

	#matches keys_zone in fastcgi_cache_path in nginx.conf
	fastcgi_cache mysite;

	#don't serve pages defined earlier
	fastcgi_cache_bypass $no_cache;

	#don't cache pages defined earlier
	fastcgi_no_cache $no_cache;

	#unsure what the impacts of this variable is
	fastcgi_max_temp_file_size 2M;

	#Use stale cache items while updating in the background
	fastcgi_cache_use_stale updating error timeout invalid_header http_500;
	fastcgi_cache_lock on;
	fastcgi_cache_lock_timeout 10s;

	add_header X-Cache $upstream_cache_status;
