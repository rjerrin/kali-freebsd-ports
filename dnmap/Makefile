# $FreeBSD$

PORTNAME=	dnmap
PORTVERSION=	0.6
DISTVERSIONPREFIX=	v
CATEGORIES=	security
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE}
MASTER_SITE_SUBDIR=	dnmap
DISTNAME=	dnmap_v${PORTVERSION}
EXTRACT_ONLY=	${DISTNAME}${EXTRACT_SUFX}

MAINTAINER=	zackj901@yandex.com
COMMENT=	Distributed nmap scans

LICENSE=	GPLv3

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}openssl>=0.15.1:${PORTSDIR}/security/py-openssl \
	  	${PYTHON_PKGNAMEPREFIX}twisted>=15.5.0:${PORTSDIR}/devel/py-twisted  \
		${PYTHON_PKGNAMEPREFIX}service_identity>=14.0.0:${PORTSDIR}/security/py-service_identity

WRKSRC=	${WRKDIR}/dnmap_v0.6

OPTIONS_DEFINE=	SERVER CLIENT
OPTIONS_SUB=	yes
SERVER_DESC=	DNMAP	SERVER
CLIENT_DESC=	DNMAP  CLIENT
OPTIONS_DEFAULT=	SERVER CLIENT

USES=		tar:tgz python:2.7+

NO_BUILD=	yes

SERVER_RUN_DEPENDS=	nmap:${PORTSDIR}/security/nmap

post-patch:
	@${REINPLACE_CMD} -e 's|env python|env python2.7|' ${WRKSRC}/${PORTNAME}_server.py
	@${REINPLACE_CMD} -e 's|server\.pem|\/usr\/local\/share\/dnmap\/server\.pem|' ${WRKSRC}/${PORTNAME}_server.py
	@${REINPLACE_CMD} -e 's|env python|env python2.7|' ${WRKSRC}/${PORTNAME}_client.py

do-install:
	${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/README       ${STAGEDIR}${DOCSDIR}

do-install-SERVER-on:
	   ${MKDIR} 	     ${STAGEDIR}${DATADIR}
	   ${INSTALL_SCRIPT} ${WRKSRC}/${PORTNAME}_server.py  ${STAGEDIR}${PREFIX}/bin/${PORTNAME}-server
	   ${INSTALL_DATA}   ${WRKSRC}/server.pem   ${STAGEDIR}${DATADIR}

do-install-CLIENT-on:
	   ${INSTALL_SCRIPT} ${WRKSRC}/${PORTNAME}_client.py  ${STAGEDIR}${PREFIX}/bin/${PORTNAME}-client

.include <bsd.port.mk>
