document.addEventListener('click', function(event) {
  window.webkit && window.webkit.messageHandlers.aidealClick.postMessage(null);
});
