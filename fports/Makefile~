PORTNAME=	0d1n
PORTVERSION=	3.8
CATEGORIES=	security

MAINTAINER=	zackj901@yandex.com
COMMENT=	Open source web HTTP fuzzing tool and bruteforcer
WWW=		https://github.com/CoolerVoid/0d1n

USES=		gmake
GNU_CONFIGURE=	yes

LICENSE=	GPLv3

LIB_DEPENDS=	libcurl.so:ftp/curl

USE_GITHUB=	yes
GH_ACCOUNT=	CoolerVoid
GH_TAGNAME=	OdinV38

PLIST_FILES=	bin/0d1n
PORTDOCS=	README.txt

OPTIONS_DEFINE=	DOCS

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/${PORTNAME} ${STAGEDIR}${PREFIX}/bin

do-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/README.txt ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
