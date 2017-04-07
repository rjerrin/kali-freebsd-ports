# $FreeBSD$

PORTNAME=	cookiecadger
PORTVERSION=	1.08
CATEGORIES=	security java
MASTER_SITES=	https://www.cookiecadger.com/files/
DISTFILES=	${DISTNAME:S/c/C/g}.jar
EXTRACT_ONLY=

MAINTAINER=	rihaz.jerrin@gmail.com
COMMENT=	Capture data from applications that utilize insecure HTTP GET requests

LICENSE=	BSD2CLAUSE

RUN_DEPENDS=	tshark:net/tshark

USE_JAVA=       yes
NO_BUILD=	yes
JAVA_VERSION=   1.7+
NO_ARCH=	yes
PLIST_FILES+=	%%JAVAJARDIR%%/CookieCadger-1.08.jar \
		bin/cookiecadger

SUB_FILES=	cookiecadger

do-install:
	  ${INSTALL_DATA} 	 ${DISTDIR}/CookieCadger-1.08.jar  ${STAGEDIR}/${JAVAJARDIR}/CookieCadger-1.08.jar
	  ${INSTALL_SCRIPT} 	 ${WRKDIR}/cookiecadger	  	   ${STAGEDIR}${PREFIX}/bin/cookiecadger

.include <bsd.port.mk>
