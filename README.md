# Nginx Configuration Template

> This repo is a collection of our Nginx configurations and optimizations for performance and security

[![Support Level](https://img.shields.io/badge/support-archived-red.svg)](#support-level)

> [!CAUTION]
> As of 12 April 2024, this project is archived and no longer being actively maintained.

## Overview

10up uses [Nginx](http://nginx.org/) as it's standard webserver software on many high traffic, enterprise [WordPress](http://wordpress.org/) sites.  This repo is a collection of our configurations and optimizations for performance and security.  For most sites, these configurations can be included as-is in your Nginx server and http blocks.  For sites that need more customization, these configurations can serve as a reference.  

## Usage

The `.inc` files in the `includes` and `security` directories are intended to be used as is with no modification.  For files like `blockxmlrpc.inc` that have options, these are controlled by variables that should be set in the `nginx.conf` file and the `.conf` file used for the specific site.  The `template` directory contains an example `nginx.conf` file and an `example.conf` file that contains the server block.  The `example.conf` file usually goes in the `/etc/nginx/conf.d/` directory or in the `/etc/nginx/sites-enabled/` directory.   

Certain security rules block pages in WordPress that can impact expected behavior in some use-cases. Notably, the WordPress "5-minute" installation pages in `wp-admin` are blocked, which will prevent an initial installation from the browser, and sites using these configs must be created with a manual `wp-config.php` file and database import, or via the WP-CLI command line tool. 

## Installation

The easiest way to use this repo is to clone it to your `/etc/nginx/` directory. All of the include file paths used in `/template/nginx.conf` and `/template/example.conf` will work without modification with this method:

1. `cd /etc/nginx/`

2.  `git clone https://github.com/10up/nginx_configs.git`

Use the `nginx.conf` file in `nginx_configs/template/` to update your existing nginx.conf file in `/etc/nginx/nginx.conf` where appropriate (you could copy the `nginx.conf` file over the existing one, but there is some potential to overwrite important settings from your install by doing this).  Copy the `example.conf` file from `nginx_configs/template/` to your `conf.d` or `sites-enabled` directory and rename it something related to the domain of the site it will configure.  In the new `example.conf` file, comment out or uncomment the `include` statements that apply to your use case.  For example, if you have a WordPress single-site install, comment out `nginx_configs/includes/wp_subdir_multisite.inc;`.  If you have a WordPress multisite subdirectory install, uncomment this line to include this file.  

After making configuration changes, remember to test first with `nginx -t` before reloading Nginx (`systemctl reload nginx` for systemd or `/etc/init.d/nginx reload` for SysVinit).

## Issues

If you identify any errors or have an idea for improving these files, please [open an issue](https://github.com/10up/nginx_configs/issues). We're excited to see what the community thinks of this project, and we would love your input!

## License

Our Nginx Configuration Template is free; you can redistribute it and/or modify it under the terms of the [GNU General Public License](http://www.gnu.org/licenses/gpl-2.0.html) as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

## Support Level

**Archived:** This project is no longer maintained by 10up. We are no longer responding to Issues or Pull Requests unless they relate to security concerns. We encourage interested developers to fork this project and make it their own!

## Like what you see?

<p align="center">
<a href="http://10up.com/contact/"><img src="https://10up.com/uploads/2016/10/10up-Github-Banner.png" width="850"></a>
</p>
