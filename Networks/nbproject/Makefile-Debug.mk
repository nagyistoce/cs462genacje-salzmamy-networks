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
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=
AS=as.exe

# Macros
CND_PLATFORM=Cygwin-Windows
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include nbMakefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/genacje_salzmamy_connector.o \
	${OBJECTDIR}/genacje_salzmamy_blowfish.o \
	${OBJECTDIR}/genacje_salzmamy_TransferProtocol.o \
	${OBJECTDIR}/genacje_salzmamy_AccuracyTest.o \
	${OBJECTDIR}/genacje_salzmamy_Node.o \
	${OBJECTDIR}/genacje_salzmamy_main.o \
	${OBJECTDIR}/genacje_salzmamy_GoBackN.o \
	${OBJECTDIR}/genacje_salzmamy_endian.o \
	${OBJECTDIR}/genacje_salzmamy_Node_KDC.o \
	${OBJECTDIR}/genacje_salzmamy_TransferMetrics.o \
	${OBJECTDIR}/genacje_salzmamy_Node_Receiver.o \
	${OBJECTDIR}/genacje_salzmamy_crc.o \
	${OBJECTDIR}/genacje_salzmamy_StopAndWait.o \
	${OBJECTDIR}/genacje_salzmamy_Node_Initiator.o


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
	"${MAKE}"  -f nbproject/Makefile-Debug.mk dist/Debug/Cygwin-Windows/networks.exe

dist/Debug/Cygwin-Windows/networks.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/Cygwin-Windows
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/networks ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/genacje_salzmamy_connector.o: genacje_salzmamy_connector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/genacje_salzmamy_connector.o genacje_salzmamy_connector.cpp

${OBJECTDIR}/genacje_salzmamy_blowfish.o: genacje_salzmamy_blowfish.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/genacje_salzmamy_blowfish.o genacje_salzmamy_blowfish.cpp

${OBJECTDIR}/genacje_salzmamy_TransferProtocol.o: genacje_salzmamy_TransferProtocol.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/genacje_salzmamy_TransferProtocol.o genacje_salzmamy_TransferProtocol.cpp

${OBJECTDIR}/genacje_salzmamy_AccuracyTest.o: genacje_salzmamy_AccuracyTest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/genacje_salzmamy_AccuracyTest.o genacje_salzmamy_AccuracyTest.cpp

${OBJECTDIR}/genacje_salzmamy_Node.o: genacje_salzmamy_Node.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/genacje_salzmamy_Node.o genacje_salzmamy_Node.cpp

${OBJECTDIR}/genacje_salzmamy_main.o: genacje_salzmamy_main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/genacje_salzmamy_main.o genacje_salzmamy_main.cpp

${OBJECTDIR}/genacje_salzmamy_GoBackN.o: genacje_salzmamy_GoBackN.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/genacje_salzmamy_GoBackN.o genacje_salzmamy_GoBackN.cpp

${OBJECTDIR}/genacje_salzmamy_endian.o: genacje_salzmamy_endian.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/genacje_salzmamy_endian.o genacje_salzmamy_endian.cpp

${OBJECTDIR}/genacje_salzmamy_Node_KDC.o: genacje_salzmamy_Node_KDC.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/genacje_salzmamy_Node_KDC.o genacje_salzmamy_Node_KDC.cpp

${OBJECTDIR}/genacje_salzmamy_TransferMetrics.o: genacje_salzmamy_TransferMetrics.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/genacje_salzmamy_TransferMetrics.o genacje_salzmamy_TransferMetrics.cpp

${OBJECTDIR}/genacje_salzmamy_Node_Receiver.o: genacje_salzmamy_Node_Receiver.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/genacje_salzmamy_Node_Receiver.o genacje_salzmamy_Node_Receiver.cpp

${OBJECTDIR}/genacje_salzmamy_crc.o: genacje_salzmamy_crc.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/genacje_salzmamy_crc.o genacje_salzmamy_crc.cpp

${OBJECTDIR}/genacje_salzmamy_StopAndWait.o: genacje_salzmamy_StopAndWait.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/genacje_salzmamy_StopAndWait.o genacje_salzmamy_StopAndWait.cpp

${OBJECTDIR}/genacje_salzmamy_Node_Initiator.o: genacje_salzmamy_Node_Initiator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/genacje_salzmamy_Node_Initiator.o genacje_salzmamy_Node_Initiator.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/Cygwin-Windows/networks.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
