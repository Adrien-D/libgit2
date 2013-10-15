	git_diff *diff;
	git_diff_format_t format;
	git_diff_line_cb print_cb;
	uint32_t flags;
	git_buf *out,
	git_diff *diff,
	git_diff_format_t format,
	git_diff_line_cb cb,
	void *payload)
	pi->format   = format;
	if (diff)
		pi->flags = diff->opts.flags;

	if (diff && diff->opts.oid_abbrev != 0)
		pi->oid_strlen = diff->opts.oid_abbrev;
	else if (!diff || !diff->repo)
static int diff_print_one_name_only(
	const git_diff_delta *delta, float progress, void *data)
{
	diff_print_info *pi = data;
	git_buf *out = pi->buf;

	GIT_UNUSED(progress);

	if ((pi->flags & GIT_DIFF_SHOW_UNMODIFIED) == 0 &&
		delta->status == GIT_DELTA_UNMODIFIED)
		return 0;

	git_buf_clear(out);

	if (git_buf_puts(out, delta->new_file.path) < 0 ||
		git_buf_putc(out, '\n'))
		return -1;

	if (pi->print_cb(delta, NULL, GIT_DIFF_LINE_FILE_HDR,
			git_buf_cstr(out), git_buf_len(out), pi->payload))
		return callback_error();

	return 0;
}

static int diff_print_one_name_status(
	if ((pi->flags & GIT_DIFF_SHOW_UNMODIFIED) == 0 && code == ' ')
	if ((pi->flags & GIT_DIFF_SHOW_UNMODIFIED) == 0 && code == ' ')
		 (pi->flags & GIT_DIFF_SHOW_UNTRACKED_CONTENT) == 0))
	const git_diff_hunk *r,
	const git_diff_hunk *range,
/* print a git_diff to an output callback */
int git_diff_print(
	git_diff *diff,
	git_diff_format_t format,
	git_diff_line_cb print_cb,
	git_diff_file_cb print_file = NULL;
	git_diff_hunk_cb print_hunk = NULL;
	git_diff_line_cb print_line = NULL;

	switch (format) {
	case GIT_DIFF_FORMAT_PATCH:
		print_file = diff_print_patch_file;
		print_hunk = diff_print_patch_hunk;
		print_line = diff_print_patch_line;
		break;
	case GIT_DIFF_FORMAT_PATCH_HEADER:
		print_file = diff_print_patch_file;
		break;
	case GIT_DIFF_FORMAT_RAW:
		print_file = diff_print_one_raw;
		break;
	case GIT_DIFF_FORMAT_NAME_ONLY:
		print_file = diff_print_one_name_only;
		break;
	case GIT_DIFF_FORMAT_NAME_STATUS:
		print_file = diff_print_one_name_status;
		break;
	default:
		giterr_set(GITERR_INVALID, "Unknown diff output format (%d)", format);
		return -1;
	}
	if (!(error = diff_print_info_init(
			&pi, &buf, diff, format, print_cb, payload)))
			diff, print_file, print_hunk, print_line, &pi);
/* print a git_patch to an output callback */
int git_patch_print(
	git_patch *patch,
	git_diff_line_cb print_cb,
			&pi, &temp, git_patch__diff(patch),
			GIT_DIFF_FORMAT_PATCH, print_cb, payload)))
		error = git_patch__invoke_callbacks(
	const git_diff_hunk *range,
/* print a git_patch to a string buffer */
int git_patch_to_str(
	git_patch *patch)
	error = git_patch_print(patch, diff_print_to_buffer_cb, &output);