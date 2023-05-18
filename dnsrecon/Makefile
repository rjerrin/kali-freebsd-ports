PORTNAME=	dnsrecon
DISTVERSION=	1.1.4
#PORTREVISION=	1
CATEGORIES=	dns

MAINTAINER=	rihaz.jerrin@gmail.com
COMMENT=	DNS enumeration tool
WWW=		https://github.com/darkoperator/dnsrecon

LICENSE=	GPLv2

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}dnspython>=2:dns/py-dnspython@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}flake8>=0:devel/py-flake8@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}lxml>=0:devel/py-lxml@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}netaddr>=0:net/py-netaddr@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pytest>=0:devel/py-pytest@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}sqlite3>=0:databases/py-sqlite3@${PY_FLAVOR}

USES=		python shebangfix
USE_GITHUB=	yes
GH_ACCOUNT=	darkoperator

SHEBANG_FILES=	${WRKSRC}/dnsrecon.py

NO_ARCH=	yes
NO_BUILD=	yes

do-install:
	${MKDIR} ${STAGEDIR}${DOCSDIR}
	${MKDIR} ${STAGEDIR}${DATADIR}
	${MKDIR} ${STAGEDIR}${PYTHONPREFIX_SITELIBDIR}/dnsrecon
	(cd ${WRKSRC}/dnsrecon && ${COPYTREE_SHARE} \* \
		${STAGEDIR}${PYTHONPREFIX_SITELIBDIR}/dnsrecon)
	${INSTALL_SCRIPT} ${WRKSRC}/dnsrecon.py ${STAGEDIR}${PREFIX}/bin/dnsrecon
	${INSTALL_DATA}	${WRKSRC}/README.md ${STAGEDIR}${DOCSDIR}/README
	${INSTALL_DATA} ${FILELIST:S|^|${WRKSRC}/|} ${STAGEDIR}${DATADIR}

.include <bsd.port.mk>
