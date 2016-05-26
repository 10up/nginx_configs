        if (!-e $request_filename) {
                rewrite /wp-admin$ $scheme://$host$uri/ permanent;
                rewrite ^(/[^/]+)?(/wp-.*) $2 last;
                rewrite ^(/[^/]+)?(/.*\.php) $2 last;
        }
