Attack A
Description of the attack: Since the user has already logged into the system, the browser has saved the cookie. Thus we can make use of it by sending 
the cookie to the mailbox through sendmail.php. We further write the javascript code, escape the symbols, and add it to the URL so that when the user 
clicks that link, his cookie will be automatically sent to the mailbox.
	
Vulnerabilities of the attack: This kind of attack can be avoided by 1.using a good escaping library and encode data on output 2. replacing all special 
characters by htmlspecialchars in PHP. If the output data is encoded and the input data has been validated, it is hard to steal the cookie by the current method. 

Attack B
Description of the attack: Since SOP doesn't prevent sending, we can make use of that to steal zoobar credits. Since the browser has saved the cookie,
 in our HTML document, we can send a transfer form with username = attacker and amount = 10 to zoobar.org with the cookie. After the transfer has 
completed, we redirect the user to another website.

Vulnerabilities of the attack: This kind of attack can be avoided by 1. adding two-factor authentication, like DUO, when the security of action is a concern.
 2. Sending a message to the user to verify the user status: since the attack can not read the message otherwise SOP is violated, the attacker won't know 
what the secret value is, and thus the transfer can not be completed. 3. Referer validation (if necessary and applicable) 

Attack C
Description of the attack: The idea of the attack is to comment out the SQL statement by modifying the username since "--" in SQL means the following 
code is a comment.

Vulnerabilities of the attack: This kind of attack can be avoided by 1. filtering out any character with special meaning 2.checking the data type by 
using the prepared statement to separate code and data.