function getContentSize() {
  var element = document.querySelector('.zc_inner');
  if (!element) return null;

  var rect = element.getBoundingClientRect();
  if (!rect) return null;

  return JSON.stringify({
    width: rect.width,
    height: rect.height
  });
}
