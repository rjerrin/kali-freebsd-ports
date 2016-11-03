# $FreeBSD$

PORTNAME=	cdpsnarf
PORTVERSION=	0.1.6
DISTVERSIONPREFIX=	v
CATEGORIES=	security
MASTER_SITES=	GH

MAINTAINER=	zackj901@yandex.com
COMMENT=	Tool to extract information from CDP packets

LICENSE=	GPLv2

LIB_DEPENDS=	libpcap.so:${PORTSDIR}/net/libpcap

USE_GITHUB=	1
GH_ACCOUNT=	Zapotek

USE_GCC=	yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/${PORTNAME} ${STAGEDIR}${PREFIX}/bin
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/README ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
