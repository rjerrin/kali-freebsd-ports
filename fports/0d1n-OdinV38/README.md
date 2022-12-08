# 0d1n
---

0d1n is a tool for automating customized attacks against web applications.
This tool is significantly faster because it uses thread pool and C language.

![Alt text](https://github.com/CoolerVoid/0d1n/blob/master/doc/images/overview1.png)
![Alt text](https://github.com/CoolerVoid/0d1n/blob/master/doc/images/tables.png)
![Alt text](https://github.com/CoolerVoid/0d1n/blob/master/doc/images/datatables.png)
0d1n is a tool for automating customized attacks against web applications.
Video demo: https://www.youtube.com/watch?v=1L22mbbVge0



Tool functions: 
---

 * Brute force login and passwords in auth forms

 * Directory disclosure ( use PATH list to the brute, and find HTTP status code )

 * Test to find SQL Injection and XSS vulnerabilities 

 * Test to find SSRF

 * Test to find Command injection

 * Options to load ANTI-CSRF token each request

 * Options to use random proxy per request

 * Options to use random useragent  per request

 * Option for keep alive test (slowloris test) 

 * other functions.

To run and install, follow these steps:
---

require libcurl-dev or libcurl-devel(on rpm linux based)

$ git clone https://github.com/CoolerVoid/0d1n/

 
It would be best if you had lib curl to run. Look at the following to install:

```  
$ sudo apt-get install libcurl-dev
or try libcurl4-de or libcurl*

if rpm distro

$ sudo yum install libcurl-devel
```

To install follow this cmd:
```
$ cd 0d1n

$ make; sudo make install USER=name_your_user; 

$ cd 0d1n_viewer; make; sudo make install USER=name_your_user; 
```

Up the view server to look at the reports online:

```
$ sudo 0d1n_view 

```

Now in another console, you can run the tool:
```

$ 0d1n

```


If you need to uninstall, follow these steps:
---


```
$ cd 0d1n; sudo make uninstall

$ cd 0d1n_view; sudo make uninstall

```

Attack examples:
---

Brute force to find the directory
```
$ 0d1n --host http://127.0.0.1/^ --payloads /opt/0d1n/payloads/dir_brute.txt --threads 500 --timeout 3 --log bartsimpsom4 --save_response
```
Note: You can change the value of threads. If you have a good machine, you can try 800, 1200 each device has a different context.


For SQL injection attack
```
$ 0d1n --host 'http://site.com/view/1^/product/^/' --payloads /opt/0d1n/payloads/sqli_list.txt --find_string_list /opt/0d1n/payloads/sqli_str2find_list.txt --log log1337 --tamper randcase --threads 800 --timeout 3 --save_response\n"
```
Note: Tamper is a resource to try to bypass the web application firewall


To brute force auth system
```
0d1n --host 'http://site.com/auth.py' --post 'user=admin&password=^' --payloads /opt/0d1n/payloads/wordlist.txt --log log007 --threads 500 --timeout 3\n"
```
Note: if you have a csrf token, you can use argv to get this token for each request and brute.


Search SQLi in hard mode in login system with csrf token:
```
0d1n  --host "http://127.0.0.1/vulnerabilities/sqli/index.php?id=^" --payloads /opt/0d1n/payloads/sqli.txt --find_string_list /opt/0d1n/payloads/find_responses.txt --token_name user_token --log logtest_fibonaci49 --cookie_jar /home/user_name/cookies.txt --save_response --tamper randcase --threads 100
```
Note: Load the cookies jar from the browser and save in cookies.txt to load.



Notes External libs
---

* To gain extreme performance, 0d1n uses a thread pool of POSIX threads. You can study this small library: 
https://github.com/Pithikos/C-Thread-Pool

* The 0d1n uses OpenBSD/NetBSD functions to work with strings something like strlcat() and strlcpy() to prevent buffer overflow.
https://man.openbsd.org/strlcpy.3


Project Overview on cloc
---

```
cooler@gentoo:~/codes$ cloc 0d1n/
     937 text files.
     532 unique files.                                          
     451 files ignored.

-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
JavaScript                     361           9951          15621          52178
C                               51           4986           4967          26642
C/C++ Header                    30           1184           2858           4295
CSS                             10            434            369           2142
HTML                             7             59              0           1616
TeX                              2             52              4            206
Markdown                         3             81              0            137
make                             4             36              9            130
Bourne Shell                     2              0              0              4
-------------------------------------------------------------------------------
SUM:                           487          16835          23846          91213
-------------------------------------------------------------------------------

```


Read the docs, and help menu when you execute the "0d1n" binary...

Do you have any doubt about 0d1n? Please create an issue in this repository. I can help you.



## To study  old versions, look at the following:

http://sourceforge.net/projects/odin-security-tool/files/?source=navbar

## Point of attention
The purpose of this tool is to use in pentest, take attention if you have a proper authorization before to use that. I do not have responsibility for your actions. You can use a hammer to construct a house or destroy it, choose the law path, don't be a bad guy, remember.

                             
