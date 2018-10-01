# $FreeBSD$

PORTNAME=	wpscan
PORTVERSION=	3.2.1
CATEGORIES=	www rubygems
MASTER_SITES=	RG

MAINTAINER=	rihaz.jerrin@gmail.com
COMMENT=	WPScan is a black box WordPress vulnerability scanner

LICENSE=	MIT

RUN_DEPENDS=	rubygem-activesupport5>=5.1.6:devel/rubygem-activesupport5 \
	        rubygem-addressable>=2.5.2:www/rubygem-addressable \
		rubygem-nokogiri>=1.8.4:textproc/rubygem-nokogiri \
		rubygem-public_suffix>=3.0.3:dns/rubygem-public_suffix \
		rubygem-progressbar>=1.9.0:devel/rubygem-progressbar \
		rubygem-typhoeus>=1.3.0:www/rubygem-typhoeus \
		rubygem-yajl-ruby>=1.3.0:devel/rubygem-yajl-ruby \
		rubygem-opt_parse_validator>=0.0.16.1:devel/rubygem-opt_parse_validator \
		rubygem-tdiff>=0.3.3:devel/rubygem-tdiff \
		rubygem-cms_scanner>=0.0.39.0:devel/rubygem-cms_scanner \
		curl>=7.61.1:ftp/curl

USES=		gem

NO_ARCH=	yes
USE_RUBY=	yes
RUBY_VER=	2.4
PLIST_FILES=    bin/wpscan

.include <bsd.port.mk>
