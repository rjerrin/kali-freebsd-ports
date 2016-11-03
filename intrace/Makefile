# $FreeBSD$

PORTNAME=       intrace
PORTVERSION=	1.5.1
CATEGORIES=	security
MASTER_SITES=	GH

MAINTAINER=	zackj901@yandex.com
COMMENT=	Enumerate IP hops using existing TCP connections

LICENSE=	GPLv2

USE_GITHUB=	1
GH_ACCOUNT=	robertswiecki
GH_TAGNAME=	ba517f7

USE_GCC=	yes
USES=		gmake

do-install:
	${INSTALL_PROGRAM}	${WRKSRC}/${PORTNAME}	${STAGEDIR}${PREFIX}/bin
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/README.md ${STAGEDIR}${DOCSDIR}/README

.include <bsd.port.mk>
