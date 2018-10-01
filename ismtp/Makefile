# $FreeBSD$

PORTNAME=	ismtp
PORTVERSION=	1.5
DISTVERSIONPREFIX= v
CATEGORIES=	security
MASTER_SITES=  	GH

MAINTAINER=	rihaz.jerrin@gmail.com
COMMENT=	Test for SMTP user enumeration,internal spoofing, and relay

LICENSE=	MIT

USES=		python:2.7

USE_GITHUB=     yes
GH_ACCOUNT=     altjx
GH_PROJECT=	ipwn
GH_TAGNAME=     32bbc05

NO_BUILD=	yes

SHEBANG_FILES=  ${WRKSRC}/iSMTP.py

do-install:
	${INSTALL_SCRIPT} ${WRKSRC}/iSMTP.py  ${STAGEDIR}${PREFIX}/bin/ismtp

PLIST_FILES= bin/ismtp

.include <bsd.port.mk>
