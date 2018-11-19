        # Microcaching
        fastcgi_cache_key "$scheme://$request_method$host$request_uri";
        fastcgi_ignore_headers Cache-Control Expires Vary;

        #Cache everything by default
        set $no_cache 0;

        #Don't cache logged in users or commenters
        if ( $http_cookie ~* "comment_author_|wordpress_(?!test_cookie)|wp-postpass_" ) {
                set $no_cache 1;
        }

        #Don't cache the following URLs
        if ($request_uri ~* "/(wp-admin/|xmlrpc.php|wp-login.php)")
        {
                set $no_cache 1;
        }
