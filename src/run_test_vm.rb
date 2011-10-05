system "make kernel"

system "VBoxManage controlvm Mint poweroff"
system "VBoxManage snapshot Mint restorecurrent" or exit
system "VBoxManage startvm Mint --type headless" or exit

console = IO.popen("socat UNIX-CONNECT:/tmp/vmconsole STDIO", "w")
console.puts 'insmod /media/sf_lua/lua.ko && echo Still alive...'
sleep 1

system "VBoxManage controlvm Mint poweroff" or exit
