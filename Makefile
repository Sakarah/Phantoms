build: release translation

release:
	mkdir -p bin/release
	cd bin/release && qmake ../../src/Phantoms.pro
	cd bin/release && make

debug:
	mkdir -p bin/debug
	cd bin/debug && qmake ../../src/Phantoms.pro CONFIG+=debug
	cd bin/debug && make

translation:
	cd i18n && ./releaseTranslations.sh

update-tr:
	cd i18n && ./updateTranslations.sh

.PHONY: release debug translation update-tr
