encoded_flag = "灩捯䍔䙻ㄶ形楴獟楮獴㌴摟潦弸弲㘶㠴挲ぽ" 

decoded_flag = ""
for i in range(0, len(encoded_flag), 1):
        i1= (ord(encoded_flag[i]))  
        mask=0xFF
        c1=mask & i1
        i1>>=8
        p=chr(i1)
        q=chr(c1)     
        decoded_flag+=p+q

print(decoded_flag)