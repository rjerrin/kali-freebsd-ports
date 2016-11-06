# $FreeBSD$

PORTNAME=       0d1n
PORTVERSION=	2.2
CATEGORIES=	security
MASTER_SITES=	GH

MAINTAINER=	zackj901@yandex.com
COMMENT=	Enumerate IP hops using existing TCP connections

LICENSE=	GPLv2

LIB_DEPENDS=	libcurl.so:${PORTSDIR}/ftp/curl

USE_GITHUB=	1
GH_ACCOUNT=	CoolerVoid
GH_TAGNAME=	61913dc

pre-build:
	@${REINPLACE_CMD}  -e '/^#include <alloca\.h>/d' ${WRKSRC}/get_csrf_token.h
	@${REINPLACE_CMD}  -e '/^#include <alloca\.h>/d' ${WRKSRC}/spider.h

do-install:
	${INSTALL_PROGRAM}	${WRKSRC}/${PORTNAME}	${STAGEDIR}${PREFIX}/bin
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/README.txt	${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
