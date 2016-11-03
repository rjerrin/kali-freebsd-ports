# $FreeBSD$

PORTNAME=	dnsmap
PORTVERSION=	0.30
CATEGORIES=	net-mgmt
MASTER_SITES=	https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/dnsmap/

MAINTAINER=	zackj901@yandex.com
COMMENT=	DNS domain name brute forcing tool

LICENSE=	GPLv2

PORTDOCS=  Changelog.txt README.txt CREDITS.txt use_cases.txt

do-install:
	 ${INSTALL_PROGRAM}  ${WRKSRC}/${PORTNAME}            ${STAGEDIR}${PREFIX}/bin/${PORTNAME}
	 ${INSTALL_SCRIPT}   ${WRKSRC}/${PORTNAME}-bulk.sh    ${STAGEDIR}${PREFIX}/bin/${PORTNAME}-bulk
	 ${MKDIR}	     ${STAGEDIR}${DATADIR}
	 ${INSTALL_DATA}     ${WRKSRC}/wordlist_TLAs.txt      ${STAGEDIR}${DATADIR}
	 ${MKDIR}  	     ${STAGEDIR}${DOCSDIR}
	 ${INSTALL_DATA}     ${PORTDOCS:S|^|${WRKSRC}/|}      ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
