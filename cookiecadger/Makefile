# $FreeBSD$

PORTNAME=	cookiecadger
PORTVERSION=	1.08
CATEGORIES=	security java
MASTER_SITES=	https://www.cookiecadger.com/files/
DISTFILES=	${DISTNAME:S/c/C/g}.jar


MAINTAINER=	rihaz.jerrin@gmail.com
COMMENT=	Capture data from applications that utilize insecure HTTP GET requests

LICENSE=	BSD2CLAUSE

RUN_DEPENDS=	tshark:${PORTSDIR}/net/tshark

EXTRACT_ONLY=    

USE_JAVA=       yes
NO_EXTRACT=	yes
JAVA_EXTRACT=	no
JAVA_VERSION=   1.7
NO_BUILD=       yes
PLIST_FILES+=	${JAVALIBDIR}/CookieCadger-1.08.jar \
		${LOCALBASE}/bin/cookiecadger

SUB_FILES=	cookiecadger.sh

do-install:
	  ${INSTALL_DATA} 	 ${WRKDIR}/CookieCadger-1.08.jar  ${STAGEDIR}/${JAVALIBDIR}
	  ${INSTALL_SCRIPT} 	 ${WRKDIR}/cookiecadger.sh	  ${STAGEDIR}${PREFIX}/bin/cookiecadger

.include <bsd.port.mk>
