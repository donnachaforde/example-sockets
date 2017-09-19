#
# Builds socket client and server
#
# Donnacha Forde, Copyright, December 2001. All rights reserved.
#

CC = gcc
CCFLAGS = -g 

#LDLIBS = -lnsl -lsocket -lstdc++
LDLIBS = 



SERVER = server
CLIENT = client


all: client server




client:
	${CC} ${CCFLAGS} ${LDLIBS} -o ${CLIENT} ${CLIENT}.cxx


server:
	${CC} ${CCFLAGS} ${LDLIBS} -o ${SERVER} ${SERVER}.cxx


clean:
	rm -rf ${SERVER}
	rm -rf ${CLIENT}
	rm -rf *.o
	rm -rf core
