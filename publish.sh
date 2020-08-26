#!/bin/bash

set -e

export LANG=en_US.UTF-8

VERSION=$(cat version.json | jq -r .version)
GIT_TAG=$VERSION
git tag -a -m "tagging $GIT_TAG" $GIT_TAG
git push -u origin $GIT_TAG
pod spec lint AppierFramework.podspec
pod trunk push AppierFramework.podspec --allow-warnings
