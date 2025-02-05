<?php
/* The format is:
 * array(
 *     "major release number" => array(
 *         "release" => array(
 *             "source/windows" => array(
 *                 "filename" => "filename.tar.bz2",
 *                 "name"     => "package name",
 *                 "sha256"   => "shasum -256",
 *                 "date"     => "this files release date",
 *                 "note"     => "this file was updated 29feb due to broken phar files..",
 *             ),
 *             "announcement" => "bool, release announcement exists in releases/?",
 *         ),
 *     ),
 * );
 */
$RELEASES = (function () {
    $data = [];

    /* PHP 8.4 Release */
    $data['8.4'] = [
        'version' => '8.4.2',
        'date' => '19 Dec 2024',
        'tags' => [], // Set to ['security'] for security releases.
        'sha256' => [
            'tar.gz' => '5d3cf82a7f4cafdcfc4f3d98f3e3ee81077ae57c709a5613cbff5834d78a7747',
            'tar.bz2' => 'ef4fe9921b885ce3b047792ab60260eaf657e22812be511d19d0e45edf984783',
            'tar.xz' => '92636453210f7f2174d6ee6df17a5811368f556a6c2c2cbcf019321e36456e01',
        ]
    ];

    /* PHP 8.3 Release */
    $data['8.3'] = [
        'version' => '8.3.15',
        'date' => '19 Dec 2024',
        'tags' => [], // Set to ['security'] for security releases.
        'sha256' => [
            'tar.gz' => '67073c3c9c56c86461e0715d9e1806af5ddffe8e6e2eb9781f7923bbb5bd67fa',
            'tar.bz2' => 'b1675a4ff730b5811b8e6a7687488c42e835e156a99776aa3e6f017abda3be98',
            'tar.xz' => '3df5d45637283f759eef8fc3ce03de829ded3e200c3da278936a684955d2f94f',
        ]
    ];

    /* PHP 8.2 Release */
    $data['8.2'] = [
        'version' => '8.2.27',
        'date' => '19 Dec 2024',
        'tags' => [], // Set to ['security'] for security releases.
        'sha256' => [
            'tar.gz' => '179cc901760d478ffd545d10702ebc2a1270d8c13471bdda729d20055140809a',
            'tar.bz2' => '6e57dbaf769a7f3deb4f0f48b8c535e671cc0a18022ed7f6ff23b50e941d4b60',
            'tar.xz' => '3eec91294d8c09b3df80b39ec36d574ed9b05de4c8afcb25fa215d48f9ecbc6b',
        ]
    ];

    /* PHP 8.1 Release */
    $data['8.1'] = [
        'version' => '8.1.31',
        'date' => '21 Nov 2024',
        'tags' => ['security'], // Set to ['security'] for security releases.
        'sha256' => [
            'tar.gz' => '618923b407c4575bfee085f00c4aaa16a5cc86d4b1eb893c0f352d61541bbfb1',
            'tar.bz2' => '0b39828b345151caf1b795d9f4b923c9887231776c33076dfc9d90a44390d0dc',
            'tar.xz' => 'c4f244d46ba51c72f7d13d4f66ce6a9e9a8d6b669c51be35e01765ba58e7afca',
        ]
    ];

    $ret = [];
    foreach ($data as $release) {
        $version = $release['version'];
        [$major] = explode('.', $version, 2);

        $info = [
            'announcement' => $release['announcement'] ?? true,
            'tags' => $release['tags'],
            'date' => $release['date'],
            'source' => [],
        ];
        foreach ($release['sha256'] as $format => $hash) {
            $info['source'][] = [
                'filename' => "php-{$version}.{$format}",
                'name' => "PHP {$version} ({$format})",
                'sha256' => $hash,
                'date' => $release['date'],
            ];
        }
        $ret[$major][$version] = $info;
    }
    return $ret;
})();

// Get latest release version and info.
function release_get_latest() {
    global $RELEASES;

    $version = '0.0.0';
    $current = null;
    foreach ($RELEASES as $versions) {
        foreach ($versions as $ver => $info) {
            if (version_compare($ver, $version) > 0) {
                $version = $ver;
                $current = $info;
            }
        }
    }

    return [$version, $current];
}
