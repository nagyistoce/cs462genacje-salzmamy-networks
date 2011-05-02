#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=Cygwin-Windows
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include nbMakefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/blowfish.o \
	${OBJECTDIR}/SelectiveRepeat.o \
	${OBJECTDIR}/Node_Initiator.o \
	${OBJECTDIR}/Node.o \
	${OBJECTDIR}/Node_Receiver.o \
	${OBJECTDIR}/endian.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/GoBackN.o \
	${OBJECTDIR}/connector.o \
	${OBJECTDIR}/Packet.o \
	${OBJECTDIR}/crc.o \
	${OBJECTDIR}/Node_KDC.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/Cygwin-Windows/networks.exe

dist/Release/Cygwin-Windows/networks.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Release/Cygwin-Windows
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/networks ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/blowfish.o: nbproject/Makefile-${CND_CONF}.mk blowfish.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/blowfish.o blowfish.cpp

${OBJECTDIR}/SelectiveRepeat.o: nbproject/Makefile-${CND_CONF}.mk SelectiveRepeat.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/SelectiveRepeat.o SelectiveRepeat.cpp

${OBJECTDIR}/Node_Initiator.o: nbproject/Makefile-${CND_CONF}.mk Node_Initiator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Node_Initiator.o Node_Initiator.cpp

${OBJECTDIR}/Node.o: nbproject/Makefile-${CND_CONF}.mk Node.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Node.o Node.cpp

${OBJECTDIR}/Node_Receiver.o: nbproject/Makefile-${CND_CONF}.mk Node_Receiver.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Node_Receiver.o Node_Receiver.cpp

${OBJECTDIR}/endian.o: nbproject/Makefile-${CND_CONF}.mk endian.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/endian.o endian.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/GoBackN.o: nbproject/Makefile-${CND_CONF}.mk GoBackN.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/GoBackN.o GoBackN.cpp

${OBJECTDIR}/connector.o: nbproject/Makefile-${CND_CONF}.mk connector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/connector.o connector.cpp

${OBJECTDIR}/Packet.o: nbproject/Makefile-${CND_CONF}.mk Packet.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Packet.o Packet.cpp

${OBJECTDIR}/crc.o: nbproject/Makefile-${CND_CONF}.mk crc.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/crc.o crc.cpp

${OBJECTDIR}/Node_KDC.o: nbproject/Makefile-${CND_CONF}.mk Node_KDC.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Node_KDC.o Node_KDC.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/Cygwin-Windows/networks.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
