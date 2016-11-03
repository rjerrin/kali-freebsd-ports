# $FreeBSD$

PORTNAME=	ismtp
PORTVERSION=	1.5
DISTVERSIONPREFIX= v
CATEGORIES=	security
MASTER_SITES=  	GH

MAINTAINER=	zackj901@yandex.com
COMMENT=	Search for a filetype in a domain

LICENSE=	MIT

USE_GITHUB=     yes
GH_ACCOUNT=     altjx
GH_PROJECT=	ipwn
GH_TAGNAME=     32bbc05

USES=		python:2.7

NO_BUILD=	yes

SHEBANG_FILES=  ${WRKSRC}/iSMTP.py

do-install:
	${INSTALL_SCRIPT} ${WRKSRC}/iSMTP.py  ${STAGEDIR}${PREFIX}/bin/ismtp

.include <bsd.port.mk>
