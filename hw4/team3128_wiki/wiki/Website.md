# Website Information
## General Info
Team 3128's website is hosted on GitHub. The entire website has been made using something called Jekyll, which is a program that converts text content into a static webpage. All of the formatting is done through HTML and CSS, and all of the webpages are written in Markdown. Because the site is hosted on GitHub, everyone on our team has the ability to edit the website.

## Editing Prerequisites
*To change information/add pages:* The ability to edit text

*To change formatting/styles:* Basic knowledge of HTML and CSS

## Website Structure
This will be a quick overview of how to edit/create pages All the information pertaining to Jekyll is on   The base of the site is written in HTML. For instance, the homepage layout is written like so:

```
<!DOCTYPE html>
<html>
  {% include head.html %}
  <body>
    {% include header.html %}
    
    <img src="/resources/home_image.jpeg" height="50px" width="100%"></img>
    <div class="page-content">
      <div class="wrapper">
        {{ content }}
      </div>
    </div>
    
    {% include footer.html %}
  </body>
</html>
```

Let's talk about everything you need to know.
 - {% include "file name here" %} - This the Jekyll's way of including HTML files in a singular line. Let's say you have code for a sidebar and you wanted to put it in the page layout. Rather than copy and pasting that code into every single page you want it in, you could just pop it in the "_include" directory and add {% include sidebar.html %} everywhere you want it
 - {{ content }} - When you create a new page with an existing layout, Jekyll will put that in place of the {{ content }} of the new HTML
 
 That's literally it.
 
## Creating Pages
Every single page on the site is created in Markdow except for the homepage . To create a new page, you need to create a new .md file and name it the name of the page. Once created, the MOST important thing to do is to specify the **front matter**. All that is is a few lines of information at the top of every page that tells the website where a page lives, what layout to use, and anything else. This is the format of front matter:

```
---
layout: "layout name"
title: "page title"
permalink: "permalink"
---
```

*layout:* REQUIRED  Our website has three layouts: "page a generic page , "stusub a page that belongs in the students directory , and "parpage a page that belongs in the parents directory 

*title:* REQUIRED  If the page should be alone, put that title. If this page should be nested under another pages, put the title of **that** page

*subtitle:* If this page is nested under another page, put the title of **this page** here

*permalink:* This page will show as http://team3128.org/"permalink". IMPORTANT: make sure the permalink begins and ends with a /. When nesting a page, the permalink will be `/'page-name'/'subpage-name'/`

From here, you just edit the page as you see sit

## Editing Pages
It's simple. Open up a page markdown, change the content, and you're done!

*A note about modifying the website: All edits are NOT ANONYMOUS and are linked to your GitHub account. We can easily rollback changes and making inappropriate or disrespectful changes will be met with conseq
uences. Use common sense and be responsible*

## Changing the Structure of the Site
TBA

## Changing the Appearance of the Site
TBA