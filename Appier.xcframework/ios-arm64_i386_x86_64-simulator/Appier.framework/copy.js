document.addEventListener('click', function(event) {
  if (event.target.hasAttribute('aid-copycode')) {
    window.webkit && window.webkit.messageHandlers.copy.postMessage(null);
  }
});
