                                dddddddd                         
      OOOOOOOOO                 d::::::d  iiii                   
    OO:::::::::OO               d::::::d i::::i                  
  OO:::::::::::::OO             d::::::d  iiii    STABLE                
 O:::::::OOO:::::::O            d:::::d                          
 O::::::O   O::::::O    ddddddddd:::::d iiiiiiinnnn  nnnnnnnn    
 O:::::O     O:::::O  dd::::::::::::::d i:::::in:::nn::::::::nn  
 O:::::O     O:::::O d::::::::::::::::d  i::::in::::::::::::::nn 
 O:::::O     O:::::Od:::::::ddddd:::::d  i::::inn:::::::::::::::n
 O:::::O     O:::::Od::::::d    d:::::d  i::::i  n:::::nnnn:::::n
 O:::::O     O:::::Od:::::d     d:::::d  i::::i  n::::n    n::::n
 O:::::O     O:::::Od:::::d     d:::::d  i::::i  n::::n    n::::n
 O::::::O   O::::::Od:::::d     d:::::d  i::::i  n::::n    n::::n
 O:::::::OOO:::::::Od::::::ddddd::::::ddi::::::i n::::n    n::::n
  OO:::::::::::::OO  d:::::::::::::::::di::::::i n::::n    n::::n
    OO:::::::::OO     d:::::::::ddd::::di::::::i n::::n    n::::n
      OOOOOOOOO        ddddddddd   dddddiiiiiiii nnnnnn    nnnnnn
=+::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::+=
Author: Antonio Costa a.k.a "Cooler_"
Contact: c00f3r[at]gmail[dot]com

COOLER LABs  lol  ::: coolerlab.wordpress.com :::

====================================================================


how too install ?

$ make
$ ./0d1n

 What this IT ?
  this is another Web fuzzer tool...
  
 need libcurl to run
  
  $ sudo apt-get install libcurl-dev
  if rpm distro
  $ sudo yum install libcurl-devel
  $ make
  $./0d1n


Examples:

Brute path:
$ ./0d1n --host 'http://host/find.php?search=!&type=^' --payloads payloads/xss-rsnake.txt -find_string_list response2find/find.txt  --log out_data22

Brute GET n Find string:
$ ./0d1n --host 'http://coolerlab.wordpress.com/^' --payloads test_list1 --find_string_list find_list_one --log thunder27

Lists of proxy: payloads/proxy_list.txt
http://www.freeproxylists.net/
