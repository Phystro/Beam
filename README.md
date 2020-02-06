# Beam

## Data/File Transmission over TCP sockets

#### Server Can Distribute('beam') to all, Clients join in to get their serving

#### How to Compile
* make

#### How to run/execute
* ./beam [OPTION]	[FILEPATH/FILE_DESTINATION]	[SERVER_IP]
	
#### Options:
* Server; -s
* Client; -c

#### Examples;
* ./beam -s /root/Desktop/log.txt 192.168.1.101
* ./beam -c /root/Downloads/ 192.168.1.134

##### Trade-offs
###### *Inability to use one extent/fragment on storage space. Will cause signifcant fragmentation. You can always defrag later.

###### More Developments ongoing

###### Tested Successfully on Kali Linux. Will do well on all Linux distros. Await for Windows/Mac later on...

##### Eccentric Tensor Labs
###### 2020
