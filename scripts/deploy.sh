#!/bin/bash -ex

git status
bundle exec jekyll build
tmpdir=$(mktemp -d)
mv _site $tmpdir
git fetch
git checkout origin/master
rm -rf *
rm -rf .gitignore
rm -rf .jekyll-cache
cp -R $tmpdir/_site/* .
git add *
git commit -am "Site published at $(date)"
git push origin HEAD:master
