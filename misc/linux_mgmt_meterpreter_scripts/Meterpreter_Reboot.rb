print_line("this is a line")
sysinfo = session.sys.config.sysinfo
print_status(sysinfo)

print_status("Rebooting")

sleep(1)

session.sys.power.reboot()
