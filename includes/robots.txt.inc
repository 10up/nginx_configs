# For internal sites that should not be discoverable by search engines,
# force the robots.txt file to disallow indexing by all bots.  
#
# Do NOT use on public sites that should show up on Google. 

location = /robots.txt {
    add_header  Content-Type  text/plain;
    return 200 "User-agent: *\nDisallow: /\n# Robots.txt controlled by Nginx";
}