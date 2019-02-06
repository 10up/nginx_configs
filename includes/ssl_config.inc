        # Uses https://mozilla.github.io/server-side-tls/ssl-config-generator/?hsts=no for reference        
        ssl_protocols             TLSv1.2;
        ssl_prefer_server_ciphers on;
        ssl_ciphers               ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-SHA384:ECDHE-RSA-AES256-SHA384:ECDHE-ECDSA-AES128-SHA256:ECDHE-RSA-AES128-SHA256;
        ssl_buffer_size           8k;
        ssl_session_cache         shared:SSL:50m;
        ssl_session_timeout       1d;
        ssl_session_tickets       off;

        resolver                  8.8.8.8;

        # HSTS (https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Strict-Transport-Security#Preloading_Strict_Transport_Security)
        add_header Strict-Transport-Security "max-age=31536000; preload";