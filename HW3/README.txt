Usage: python scanner.py example.pcap
Output: ARP spoofing message comes first, then Port Scan message, finally SYN flood message. End with new line

Description of each scanner
0. General Idea: using pcap reader from dpkt, go through each packet in pcap file, apply filters on the packet according to different scanner
1. ARP spoofing scanner: filter out ARP layer, if the spa is one of the ip we need to protect but sha is different to the correct mac address, report arp spoofing.
2. Port scan: filter out TCP and UDP layer, for TCP, check it is indeed SYN, store dst, port, frame_num in a nested dict and avoid duplications, aftering looping out all packet, go over the dict and ouput Port scan message if any dst received more than 100 message.
3. SYN flood: filter out TCP layer, check it is indeed TCP_SYN, store dest_ip, frame, port, timestamp in dictionary and for each dest_ip, keep only records within 1 second, check each time, if any dest_ip hs more than 100 record, report syn flood and mark it as reported to avoid duplicaiton.