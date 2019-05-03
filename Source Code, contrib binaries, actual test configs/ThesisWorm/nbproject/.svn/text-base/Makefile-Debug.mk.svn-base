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
FC=gfortran
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/md5.o \
	${OBJECTDIR}/Configuration.o \
	${OBJECTDIR}/logger.o \
	${OBJECTDIR}/exploit_metasploit_upexec.o \
	${OBJECTDIR}/Utilities.o \
	${OBJECTDIR}/Exploit.o \
	${OBJECTDIR}/exploit_payload_thesiswormremoteloader.o \
	${OBJECTDIR}/utf8_codecvt_facet.o \
	${OBJECTDIR}/ThesisWorm.o \
	${OBJECTDIR}/ArgumentParser.o \
	${OBJECTDIR}/TCPClient.o


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
LDLIBSOPTIONS=-L/C/boost_1_48_0/stage/lib -static -lws2_32 -lboost_filesystem-mgw46-s-1_48 -lboost_date_time-mgw46-s-1_48 -lboost_system-mgw46-s-1_48 -lboost_regex-mgw46-s-1_48

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/thesisworm.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/thesisworm.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -T ./LinkerScript -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/thesisworm ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/md5.o: md5.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -I/C/boost_1_48_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/md5.o md5.cpp

${OBJECTDIR}/Configuration.o: Configuration.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -I/C/boost_1_48_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Configuration.o Configuration.cpp

${OBJECTDIR}/logger.o: logger.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -I/C/boost_1_48_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/logger.o logger.cpp

${OBJECTDIR}/exploit_metasploit_upexec.o: exploit_metasploit_upexec.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -I/C/boost_1_48_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/exploit_metasploit_upexec.o exploit_metasploit_upexec.cpp

${OBJECTDIR}/Utilities.o: Utilities.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -I/C/boost_1_48_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Utilities.o Utilities.cpp

${OBJECTDIR}/Exploit.o: Exploit.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -I/C/boost_1_48_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Exploit.o Exploit.cpp

${OBJECTDIR}/exploit_payload_thesiswormremoteloader.o: exploit_payload_thesiswormremoteloader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -I/C/boost_1_48_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/exploit_payload_thesiswormremoteloader.o exploit_payload_thesiswormremoteloader.cpp

${OBJECTDIR}/utf8_codecvt_facet.o: utf8_codecvt_facet.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -I/C/boost_1_48_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/utf8_codecvt_facet.o utf8_codecvt_facet.cpp

${OBJECTDIR}/ThesisWorm.o: ThesisWorm.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -I/C/boost_1_48_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ThesisWorm.o ThesisWorm.cpp

${OBJECTDIR}/ArgumentParser.o: ArgumentParser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -I/C/boost_1_48_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ArgumentParser.o ArgumentParser.cpp

${OBJECTDIR}/TCPClient.o: TCPClient.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -I/C/boost_1_48_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/TCPClient.o TCPClient.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/thesisworm.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
