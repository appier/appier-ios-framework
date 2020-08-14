#!/usr/bin/env groovy

pipeline {
  agent {
    label "mobile-mac-mini"
  }

  stages {
    stage('build') {
      steps {
        step([$class: 'WsCleanup'])
        checkout scm
        sh "$WORKSPACE/publish.sh"
      }
    }
  }
}
