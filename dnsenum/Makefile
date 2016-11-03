# Created by: Rihaz Jerrin <zackj901@yandex.com>
# $FreeBSD: head/security/cisco-torch/Makefile 412349 2016-04-01 14:25:16Z mat $

PORTNAME=	dnsenum
PORTVERSION=	1.2.4.2
CATEGORIES=	dns
MASTER_SITES=	GH

MAINTAINER=	zackj901@yandex.com
COMMENT=	Enumerate DNS information  and to discover non-contiguous ip blocks

LICENSE=	GPLv2

RUN_DEPENDS=	p5-Net-IP>=0:${PORTSDIR}/net-mgmt/p5-Net-IP \
		p5-Net-DNS>=0:${PORTSDIR}/dns/p5-Net-DNS \
		p5-Net-Netmask>=0:${PORTSDIR}/net-mgmt/p5-Net-Netmask \
		p5-Net-Whois>=0:${PORTSDIR}/net/p5-Net-Whois \
		p5-HTML-Parser>=0:${PORTSDIR}/www/p5-HTML-Parser \
                p5-WWW-Mechanize>=0:${PORTSDIR}/www/p5-WWW-Mechanize \
		p5-XML-Writer>=0:${PORTSDIR}/textproc/p5-XML-Writer \
		p5-String-Random>=0:${PORTSDIR}/devel/p5-String-Random

USES=		perl5 shebangfix
SHEBANG_FILES=	${WRKSRC}/dnsenum.pl

NO_BUILD=	yes
NO_ARCH=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	fwaeytens

do-install:
	${INSTALL_SCRIPT}   ${WRKSRC}/dnsenum.pl 	  ${STAGEDIR}${PREFIX}/bin/dnsenum
	${MKDIR}	    ${STAGEDIR}${DATADIR}
	${MKDIR}	    ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA}	    ${WRKSRC}/README.md	 	  ${STAGEDIR}${DOCSDIR}/README
	${INSTALL_DATA}	    ${WRKSRC}/INSTALL.txt  	  ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA}     ${WRKSRC}/dns.txt		  ${STAGEDIR}${DATADIR}

.include <bsd.port.mk>
