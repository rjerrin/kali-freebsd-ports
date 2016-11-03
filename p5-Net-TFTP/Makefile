# $FreeBSD: head/net-mgmt/p5-Cisco-CopyConfig/Makefile 411797 2016-03-24 15:34:42Z amdmi3 $

PORTNAME=       Net-TFTP
PORTVERSION=	0.19
CATEGORIES=	net perl5
MASTER_SITES=	CPAN
MASTER_SITE_SUBDIR=	CPAN:SAPER
PKGNAMEPREFIX=	p5-

MAINTAINER=	zackj901@yandex.com
COMMENT=	Net::TFTP module 

BUILD_DEPENDS=	p5-Net-SNMP>=0:${PORTSDIR}/net-mgmt/p5-Net-SNMP
RUN_DEPENDS=	p5-Net-SNMP>=0:${PORTSDIR}/net-mgmt/p5-Net-SNMP

USES=		perl5
USE_PERL5=	configure
NO_ARCH=	yes

.include <bsd.port.mk>
