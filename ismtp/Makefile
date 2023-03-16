# $FreeBSD$

PORTNAME=	ismtp
DISTVERSION=	g20190921
CATEGORIES=	security
MASTER_SITES=	GH

MAINTAINER=	rihaz.jerrin@gmail.com
COMMENT=	Test for SMTP user enumeration,internal spoofing, and relay

LICENSE=	MIT

USES=	python:3.0+  shebangfix

USE_GITHUB=	yes
GH_ACCOUNT=	altjx
GH_PROJECT=	ipwn
GH_TAGNAME=	18198ad
#GH_SUBDIR=	iSMTP

NO_BUILD=	yes

SHEBANG_FILES=	${WRKSRC}/iSMTP/iSMTP.py

PLIST_FILES=	bin/ismtp

do-install:
	${INSTALL_SCRIPT} ${WRKSRC}/iSMTP/iSMTP.py  ${STAGEDIR}${PREFIX}/bin/ismtp

.include <bsd.port.mk>
