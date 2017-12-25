#!/bin/bash
pkgbuild --identifier me.ngomez.sc4.MacInjector --root Root --version "0.9.0" --scripts scripts --install-location / me.ngomez.sc4.MacInjector.install.pkg
productbuild --distribution distribution.xml --resources resources/ "SC4MacInjector.pkg"
