# $FreeBSD$

PORTNAME=	miranda
PORTVERSION=	1.0
CATEGORIES=	security
MASTER_SITES=  	https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/mirandaupnptool/

MAINTAINER=	zackj901@yandex.com
COMMENT=	Search for a filetype in a domain

LICENSE=	MIT

USES=		python:2.7
SHEBANG_FILES=  ${WRKSRC}/miranda.py

NO_BUILD=	yes

WRKSRC=		${WRKDIR}

do-install:
	    ${INSTALL_SCRIPT}	     ${WRKSRC}/${PORTNAME}.py  	${STAGEDIR}${PREFIX}/bin/${PORTNAME}
	    ${MKDIR}	${STAGEDIR}${DOCSDIR}
	    ${INSTALL_DATA}	${WRKSRC}/ENUMHOSTS	${STAGEDIR}${DOCSDIR}
	    ${INSTALL_DATA}	${WRKSRC}/README.TXT	${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
