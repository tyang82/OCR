cmd_Release/obj.target/addon.node := g++ -shared -pthread -rdynamic -m64  -Wl,-soname=addon.node -o Release/obj.target/addon.node -Wl,--start-group Release/obj.target/addon/test.o Release/obj.target/addon/person.o -Wl,--end-group 
