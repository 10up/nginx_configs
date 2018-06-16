Nginx Configuration Template
========

10up uses [Nginx] (http://nginx.org/) as it's standard webserver software on many high traffic, enterprise [WordPress](http://wordpress.org/) sites.  This repo is a collection of our configurations and optimizations for performance and security that we've collected as a standard that can be used on most sites.  For most sites, these configurations can be included as-is in your Nginx server block.  For sites that need more customization, these configurations can serve as a reference.  

<p align="center">
<a href="http://10up.com/contact/"><img src="https://10updotcom-wpengine.s3.amazonaws.com/uploads/2016/10/10up-Github-Banner.png" width="850"></a>
</p>

## Usage
The `.inc` files in the `includes` and `security` directories are intended to be used as is with no modification.  For files like `blockxmlrpc.inc` that have options, these are controlled by variables that should be set in the `nginx.conf` file and the `.conf` file used for the specific site.  The `template` directory contains an example `nginx.conf` file and `example.conf` file that contains the server block.  The `example.conf` file usually goes in the `/etc/nginx/conf.d/` directory or in the `/etc/nginx/sites-enabled/` directory.   

## Installation
The easiest way to use this repo is to clone it to your `/etc/nginx/` directory. All of the include file paths used in `/template/nginx.conf` and `/template/example.conf` will work without modification with this method:

1. `cd /etc/nginx/`

2.  `git clone https://github.com/10up/nginx_configs.git`

Use the `nginx.conf` file in `nginx_configs/template/` to update your existing nginx.conf file in `/etc/nginx/nginx.conf` where appropriate (you could copy the `nginx.conf` file over the existing one, but there is some potential to overwrite important settings from your install by doing this).  Copy the `example.conf` file from `nginx_configs/template/` to your `conf.d` or `sites-enabled` directory and rename it something related to the domain of the site it will configure.  In the new `example.conf` file, comment out or uncomment the `include` statements that apply to your use case.  For example, if you have a WordPress single-site install, comment out `nginx_configs/includes/wp_subdir_multisite.inc;`.  If you have a WordPress multisite subdirectory install, uncomment this line to include this file.  

## Issues

If you identify any errors or have an idea for improving these files, please [open an issue](https://github.com/10up/nginx_configs/issues). We're excited to see what the community thinks of this project, and we would love your input!

## License

Our Nginx Configuration Template is free; you can redistribute it and/or modify it under the terms of the [GNU General Public License](http://www.gnu.org/licenses/gpl-2.0.html) as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
