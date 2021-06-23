document.addEventListener('click', function(event) {
  if (event.target.hasAttribute('aid-close')) {
    window.webkit && window.webkit.messageHandlers.aidealDismiss.postMessage(null);
  }
});
