# $FreeBSD$

PORTNAME=	goofile
PORTVERSION=	1.5
DISTVERSIONPREFIX= v
CATEGORIES=	security
MASTER_SITES=  	https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/goofile/
DISTNAME=	${PORTNAME}v${PORTVERSION}

MAINTAINER=	zackj901@yandex.com
COMMENT=	Search for a filetype in a domain

LICENSE=	MIT

RUN_DEPENDS	= ${PYTHON_PKGNAMEPREFIX}requests>=0:${PORTSDIR}/www/py-requests
USES=		zip  python:2.7

NO_BUILD=	yes

SHEBANG_FILES=  ${WRKSRC}/goofile.py

do-install:
	${INSTALL_SCRIPT} ${WRKSRC}/${PORTNAME}.py  ${STAGEDIR}${PREFIX}/bin/${PORTNAME}

.include <bsd.port.mk>
