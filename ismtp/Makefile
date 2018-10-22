# $FreeBSD$

PORTNAME=	ismtp
PORTVERSION=	1.5
DISTVERSIONPREFIX= v
CATEGORIES=	security
MASTER_SITES=  	GH

MAINTAINER=	rihaz.jerrin@gmail.com
COMMENT=	Test for SMTP user enumeration,internal spoofing, and relay

LICENSE=	MIT

USES=           python:2.7  shebangfix
SHEBANG_GLOB=   *.py

USE_GITHUB=     yes
GH_ACCOUNT=     altjx
GH_PROJECT=	ipwn
GH_TAGNAME=     32bbc05

NO_BUILD=	yes

PLIST_FILES= bin/ismtp

do-install:
	${INSTALL_SCRIPT} ${WRKSRC}/iSMTP.py  ${STAGEDIR}${PREFIX}/bin/ismtp


.include <bsd.port.mk>
