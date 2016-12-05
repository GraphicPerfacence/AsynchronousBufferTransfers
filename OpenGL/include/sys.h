//
//  sys.h
//  OpenGL
//
//  Created by xt on 16/1/30.
//  Copyright (c) 2016Äê xt. All rights reserved.
//

/*
   The operating system, must be one of: (Q_OS_x)

	 MACX   - Mac OS X
	 MAC9   - Mac OS 9
	 MSDOS  - MS-DOS and Windows
	 OS2    - OS/2
	 OS2EMX - XFree86 on OS/2 (not PM)
	 WIN32  - Win32 (Windows 95/98/ME and Windows NT/2000/XP)
	 CYGWIN - Cygwin
	 SOLARIS    - Sun Solaris
	 HPUX   - HP-UX
	 ULTRIX - DEC Ultrix
	 LINUX  - Linux
	 FREEBSD    - FreeBSD
	 NETBSD - NetBSD
	 OPENBSD    - OpenBSD
	 BSDI   - BSD/OS
	 IRIX   - SGI Irix
	 OSF    - HP Tru64 UNIX
	 SCO    - SCO OpenServer 5
	 UNIXWARE   - UnixWare 7, Open UNIX 8
	 AIX    - AIX
	 HURD   - GNU Hurd
	 DGUX   - DG/UX
	 RELIANT    - Reliant UNIX
	 DYNIX  - DYNIX/ptx
	 QNX    - QNX
	 QNX6   - QNX RTP 6.1
	 LYNX   - LynxOS
	 BSD4   - Any BSD 4.4 system
	 UNIX   - Any UNIX BSD/SYSV system
*/

// #include <windows.h>



#if defined(__APPLE__) 
#  define X_OS_MACX   
#elif defined(__MACOSX__)   
#  define X_OS_MACX   
#elif defined(macintosh)   
#  define X_OS_MAC9   
#elif defined(__CYGWIN__)   
#  define X_OS_CYGWIN   
#elif defined(MSDOS) || defined(_MSDOS)   
#  define X_OS_MSDOS   
#elif defined(__OS2__)   
#  if defined(__EMX__)   
#    define X_OS_OS2EMX   
#  else   
#    define X_OS_OS2   
#  endif   
#elif !defined(SAG_COM) && (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))   
#  define X_OS_WIN32   
#  define X_OS_WIN64   
#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))   
#  define X_OS_WIN32   
#elif defined(__MWERKS__) && defined(__INTEL__)   
#  define X_OS_WIN32   
#elif defined(__sun) || defined(sun)   
#  define X_OS_SOLARIS   
#elif defined(hpux) || defined(__hpux)   
#  define X_OS_HPUX   
#elif defined(__ultrix) || defined(ultrix)   
#  define X_OS_ULTRIX   
#elif defined(sinix)   
#  define X_OS_RELIANT   
#elif defined(__linux__) || defined(__linux)   
#  define X_OS_LINUX   
#elif defined(__FreeBSD__)   
#  define X_OS_FREEBSD   
#  define X_OS_BSD4   
#elif defined(__NetBSD__)   
#  define X_OS_NETBSD   
#  define X_OS_BSD4   
#elif defined(__OpenBSD__)   
#  define X_OS_OPENBSD   
#  define X_OS_BSD4   
#elif defined(__bsdi__)   
#  define X_OS_BSDI   
#  define X_OS_BSD4   
#elif defined(__sgi)   
#  define X_OS_IRIX   
#elif defined(__osf__)   
#  define X_OS_OSF   
#elif defined(_AIX)   
#  define X_OS_AIX   
#elif defined(__Lynx__)   
#  define X_OS_LYNX   
#elif defined(__GNU_HURD__)   
#  define X_OS_HURD   
#elif defined(__DGUX__)   
#  define X_OS_DGUX   
#elif defined(__QNXNTO__)   
#  define X_OS_QNX6   
#elif defined(__QNX__)   
#  define X_OS_QNX   
#elif defined(_SEQUENT_)   
#  define X_OS_DYNIX   
#elif defined(_SCO_DS)                   /* SCO OpenServer 5 + GCC */   
#  define X_OS_SCO   
#elif defined(__USLC__)                  /* all SCO platforms + UDK or OUDK */   
#  define X_OS_UNIXWARE   
#  define X_OS_UNIXWARE7   
#elif defined(__svr4__) && defined(i386) /* Open UNIX 8 + GCC */   
#  define X_OS_UNIXWARE   
#  define X_OS_UNIXWARE7   
#else   
#  error "Qt has not been ported to this OS - talk to qt-bugs@trolltech.com"   
#endif   

#if defined(Q_OS_MAC9) || defined(Q_OS_MACX)   
#  define X_OS_MAC   
#endif   

#if defined(Q_OS_MAC9) || defined(Q_OS_MSDOS) || defined(Q_OS_OS2) || defined(Q_OS_WIN32) || defined(Q_OS_WIN64)   
#  undef X_OS_UNIX   
#elif !defined(Q_OS_UNIX)   
#  define X_OS_UNIX   
#endif  