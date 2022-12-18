PORTNAME=	gospider
PORTVERSION=	1.1.6
DISTVERSIONPREFIX=	v
CATEGORIES=	www

MAINTAINER=	zackj901@yandex.com
COMMENT=	Web spider written in Go
WWW=	https://github.com/jaeles-project/gospider

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=	go:modules
USE_GITHUB=	yes
GH_ACCOUNT=	jaeles-project
GO_MODULE=	github.com/jaeles-project/gospider

PLIST_FILES=	bin/gospider
PORTDOCS=	README.md
GO_TARGET=	gospider

OPTIONS_DEFINE=	DOCS

do-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/README.md    ${STAGEDIR}${DOCSDIR}/README.txt

.include <bsd.port.mk>
